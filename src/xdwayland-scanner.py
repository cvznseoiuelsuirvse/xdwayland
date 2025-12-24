#!/usr/bin/python3

from io import TextIOWrapper
import xml.etree.ElementTree as ET
import os
import sys


def generate_comment(text: str) -> str:
    ret = []
    text = text.strip()
    lines = text.splitlines()
    line_c = len(lines)

    for i, line in enumerate(lines):
        line = line.strip()

        if i == 0:
            row = f"/* {line}"

        else:
            row = f"* {line}"

        if i == line_c - 1:
            row += f" */"

        ret.append(row)

    return "\n".join(ret)


def generate_requests(interface_name: str, cur: ET.Element, *, header: bool) -> tuple[str, str] | None:
    if cur.find("./request") is not None:
        requests = ""
        requests_array = f"static const struct xdwl_method xd{interface_name}_requests[] = {{\n"

        for i, request in enumerate(cur.findall("./request")):
            request_name = request.get("name")
            request_description = request.find("./description")

            request_struct = f'    {{"{request_name}", '

            if header and request_description is not None and request_description.text:
                method = generate_comment(request_description.get("summary", "") + "\n" + request_description.text) + "\n"
            else:
                method = ""

            method += f"int xd{interface_name}_{request_name}(xdwl_proxy *proxy, "
            if interface_name != "wl_display":
                method += f"xdwl_id {interface_name}_id, "

            args = []
            signature = ""

            if interface_name == "wl_registry" and request_name == "bind":
                method += "uint32_t _name, const char *_interface, uint32_t _version, xdwl_id _new_id, "
                args = ["_name", "_interface", "_version", "_new_id"]
                signature = "usuu"

            else:
                for arg in request.findall("./arg"):
                    arg_name = "_" + arg.get("name", "")
                    arg_type = arg.get("type")
                    args.append(arg_name)

                    match arg_type:
                        case "int" | "enum":
                            method += f"int32_t {arg_name}"
                            signature += "i"

                        case "uint" | "new_id" | "object":
                            method += f"xdwl_id {arg_name}"
                            signature += "u"

                        case "fd":
                            method += f"int {arg_name}"
                            signature += "h"

                        case "fixed":
                            method += f"float {arg_name}"
                            signature += "f"

                        case "string":
                            method += f"const char *{arg_name}"
                            signature += "s"

                    method += ", "

            method = method.rstrip(", ")
            method += ")"

            if not header:
                method += " {\n"
                if args:
                    if interface_name != "wl_display":
                        method += f'    return xdwl_send_request(proxy, {interface_name}_id, "{interface_name}", {i}, {len(args)}, {", ".join(args)});\n'
                    else:
                        method += f'    return xdwl_send_request(proxy, 1, "{interface_name}", {i}, {len(args)}, {", ".join(args)});\n'

                    request_struct += f'{len(args)}, "{signature}"}},\n'

                else:
                    if interface_name != "wl_display":
                        method += f'    return xdwl_send_request(proxy, {interface_name}_id, "{interface_name}", {i}, 0);\n'
                    else:
                        method += f'    return xdwl_send_request(proxy, 1, "{interface_name}", {i}, 0);\n'

                    request_struct += f"0, NULL}},\n"

                method += "}"

            method += ";"

            requests_array += request_struct
            requests += method + "\n"

        requests_array += "};"
        return requests, requests_array


def generate_add_listener(interface_name: str, cur: ET.Element, *, header: bool) -> str:
    if header:
        listener = f"XDWL_MUST_CHECK int xd{interface_name}_add_listener(xdwl_proxy *proxy, struct xd{interface_name}_event_handlers *event_handlers, void *user_data);"

    else:
        listener = f"""int xd{interface_name}_add_listener(xdwl_proxy *proxy, struct xd{interface_name}_event_handlers *event_handlers, void *user_data) {{
      return xdwl_add_listener(proxy, \"{interface_name}\", event_handlers, sizeof(void *) * {len(cur.findall("./event"))}, user_data);
}};"""

    return listener


def generate_events(interface_name: str, cur: ET.Element, *, header: bool) -> tuple[str, str] | None:
    if cur.find("./event") is not None:
        if not header:
            event_handlers = f"struct xd{interface_name}_event_handlers;"
        else:
            event_handlers = f"""struct xd{interface_name}_event_handlers {{
"""
        event_array = f"static const struct xdwl_method xd{interface_name}_events[] = {{\n"

        for event in cur.findall("./event"):
            event_name = event.get("name")
            event_description = event.find("./description")
            event_struct = f'    {{"{event_name}", '

            if header:
                if event_description is not None and event_description.text:
                    event_handlers += "\n" + generate_comment(event_description.get("summary", "") + "\n" + event_description.text) + "\n"

                event_handlers += f"  xdwl_event_handler(*{event.get('name')});\n\n"

            else:
                args = []
                signature = ""

                for arg in event.findall("./arg"):
                    arg_name = "_" + arg.get("name", "")
                    arg_type = arg.get("type")
                    args.append(arg_name)

                    match arg_type:
                        case "int" | "enum":
                            signature += "i"

                        case "uint" | "new_id" | "object":
                            signature += "u"

                        case "fd":
                            signature += "h"

                        case "fixed":
                            signature += "f"

                        case "string":
                            signature += "s"

                if args:
                    event_struct += f'{len(args)}, "{signature}"}},\n'

                else:
                    event_struct += f"0, NULL}},\n"

                event_array += event_struct

        if header:
            event_handlers += "};"

        event_array += "};"
        return event_handlers, event_array


def generate_enum(interface_name: str, cur: ET.Element) -> str | None:
    enum_t = ""

    for enum in cur.findall("./enum"):
        enum_name = enum.get("name")
        enum_base_name = f"xd{interface_name}_{enum_name}"

        enum_t += f"""enum {enum_base_name} {{
"""

        for entry in enum.findall("./entry"):
            entry_name = entry.get("name")
            assert entry_name
            entry_value = entry.get("value")
            assert entry_value

            entry_summary = entry.get("summary")

            if entry_summary:
                enum_t += "\n  " + generate_comment(entry_summary) + "\n"

            enum_t += f"  {enum_base_name.upper()}_{entry_name.upper()} = {entry_value},\n"

        enum_t += "};\n\n"

    return enum_t


def generate_interface_struct(cur: ET.Element, interface_name: str) -> str:
    struct = f"""const struct xdwl_interface xd{interface_name}_interface = {{
    .name = \"{interface_name}\",
"""

    if cur.find("./request") is not None:
        struct += f"    .requests = xd{interface_name}_requests,\n"

    if cur.find("./event") is not None:
        struct += f"    .events = xd{interface_name}_events,\n"

    struct += "};"

    return struct


def generate_interface(cur: ET.Element, h: TextIOWrapper, c: TextIOWrapper) -> str:
    interface_name = cur.get("name")
    assert interface_name

    interface_description = cur.find("./description")
    assert interface_description is not None and interface_description.text

    interface_description = generate_comment(interface_description.text)

    enum = generate_enum(interface_name, cur)
    if enum:
        h.write(enum + "\n")

    requests_h = generate_requests(interface_name, cur, header=True)
    requests_c = generate_requests(interface_name, cur, header=False)

    events_h = generate_events(interface_name, cur, header=True)
    events_c = generate_events(interface_name, cur, header=False)

    if events_h and events_c:
        h.write("\n" + events_h[0] + "\n")
        h.write(generate_add_listener(interface_name, cur, header=True) + "\n\n")

        c.write("\n" + events_c[0])
        c.write(generate_add_listener(interface_name, cur, header=False) + "\n\n")

    if requests_h and requests_c:
        h.write("\n" + requests_h[0] + "\n")
        c.write("\n" + requests_c[0] + "\n")

    if requests_c:
        c.write(requests_c[1] + "\n")

    if events_c:
        c.write(events_c[1] + "\n")

    c.write(generate_interface_struct(cur, interface_name))
    return f"xd{interface_name}_interface"


def generate(input: str, output_path_base: str) -> None:
    tree = ET.parse(input)
    root = tree.getroot()

    output_h = output_path_base + ".h"
    output_c = output_path_base + ".c"

    h = open(output_h, "w")
    c = open(output_c, "w")

    h_guard = f"__XDWAYLAND_{os.path.basename(output_path_base).upper().replace('-', '_')}"
    h.write(
        f"""#ifndef {h_guard}
#define {h_guard}

"""
    )

    c.write(
        f"""#include "xdwayland-client.h"
#include "xdwayland-core.h"

"""
    )

    h.write(
        f"""#include "xdwayland-client.h"

"""
    )
    interfaces = []
    for interface in root.findall("./interface"):
        interfaces.append(generate_interface(interface, h, c))


    c.write("\n\n\n__attribute__((constructor)) static void add_interfaces() {\n")
    for iface in interfaces:
        c.write(f"  xdwl_interface_register(&{iface});\n")
    c.write("}")

    h.write("\n#endif")

    h.close()
    c.close()


def main():
    if len(sys.argv) != 3:
        print("Usage: xdwayland-scanner <path-to-protocol> <output-basename>")
        return

    path = sys.argv[1]
    abs_path = os.path.abspath(path)
    basename = sys.argv[2]

    generate(abs_path, basename)


main()
