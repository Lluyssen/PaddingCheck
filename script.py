import os
import re
from pathlib import Path

def extract_structs_from_file(file_path: Path):
    with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
        code = f.read()

    struct_pattern = re.compile(r'struct\s+(\w+)\s*{([^}]+)}\s*;', re.MULTILINE | re.DOTALL)
    field_pattern = re.compile(r'\s*([a-zA-Z_:<>0-9\s]+?)\s+(\w+)(\[[^\]]+\])?\s*;', re.MULTILINE)

    structs = []

    for struct_match in struct_pattern.finditer(code):
        struct_name = struct_match.group(1)
        struct_body = struct_match.group(2)

        fields = []
        for field_match in field_pattern.finditer(struct_body):
            raw_type = field_match.group(1).strip()
            field_name = field_match.group(2)
            array_suffix = field_match.group(3) or ""
            full_type = (raw_type + array_suffix).strip()
            fields.append((full_type, field_name))

        structs.append((struct_name, fields))

    return structs

def generate_layout_cpp(structs, header_files):
    includes = [f'#include "{h}"' for h in header_files]
    base_includes = ['#include "padding.hpp"', '#include <array>']
    lines = base_includes + includes + ['', 'int main() {']

    for struct_name, fields in structs:
        type_list = ", ".join(t for t, _ in fields)
        lines.append(f'    checkStructPadding<{struct_name}, {type_list}>("{struct_name}");')

    lines.append('    return 0;')
    lines.append('}')
    return "\n".join(lines)

def collect_structs_from_dir(directory: Path):
    structs = []
    headers_included = set()
    files = list(directory.rglob("*.h*")) + list(directory.rglob("*.cpp"))
    for file in files:
        if file.is_file():
            rel_path = str(file.relative_to(directory))
            headers_included.add(rel_path)
            structs += extract_structs_from_file(file)
    return structs, sorted(headers_included)

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Génère un layout.cpp pour analyser le padding.")
    parser.add_argument("--dir", type=str, required=True, help="Dossier contenant les fichiers à scanner.")
    parser.add_argument("--out", type=str, default="layout.cpp", help="Fichier C++ de sortie.")
    args = parser.parse_args()

    structs, headers = collect_structs_from_dir(Path(args.dir))
    code = generate_layout_cpp(structs, headers)

    with open(args.out, "w", encoding="utf-8") as f:
        f.write(code)

    print(f"[OK] {args.out} généré avec {len(structs)} struct(s).")