from pathlib import Path
import sys

path = Path(__file__).resolve().parent / "migrations"

files = sorted(path.glob('*.up.sql'))

header = """#pragma once
#include "migration.hpp"
#include <array>

inline constexpr std::array migrations{
"""
footer = """};\n"""

def get_migration_string(filename, sql):
    return f'   Migration{{"{filename}",R"({sql})"}},\n'

output = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("build/generated/migrations.generated.hpp")
output.parent.mkdir(parents=True, exist_ok=True)
with output.open(mode='w', encoding="utf-8") as out:
    out.write(header)
    for item in files:
        with open(item, mode='r', encoding="utf-8") as file:
            sql = file.read()
            out.write(get_migration_string(item.name, sql))
    out.write(footer)
