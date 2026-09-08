# AGENTS.md

C++ banking-system desktop app (SDL2 + ImGui GUI) backed by MariaDB. Built with CMake; all third-party deps come from **Conan 2** (`conanfile.py`), not apt.

## Build (local, canonical)

```bash
conan install . --build=missing          # generates build/Release/generators/CMakePresets.json
cmake --preset conan-release              # preset comes from CMakeUserPresets.json -> conan output
cmake --build --preset conan-release
```

- `conanfile.py` also copies imgui's SDL2/SDLrenderer binding sources into `bindings/` on every `conan install`. Those files are git-tracked but treated as generated — don't hand-edit them, and don't add new ones there.
- CI instead installs system packages (libmariadb-dev, libspdlog-dev, libsdl2-dev, libgtest-dev) and runs plain `cmake .. && make` with no Conan; either path must keep working.

## Runtime: DB credentials come from the environment, never hardcoded

Commit history explicitly removed a hardcoded DB password; preserve this invariant.

- `BKSYS_DB_PASSWORD` is **required** — `src/main.cpp` refuses to start without it.
- Optional, with defaults: `BKSYS_DB_HOST` (localhost), `BKSYS_DB_USER` (`SERVER`), `BKSYS_DB_NAME` (`bksysDB`), `BKSYS_DB_PORT` (3306), `BKSYS_DB_SOCKET` (`/var/lib/mysql/mysql.sock`).
- **Config precedence: env var > `config.json` > default.** `config.json` (repo root) holds only non-secret DB settings loaded by the `ConfigurationManager` module. Never add a `password` key to it — the password is env-only.

## What is (and isn't) built

Root `CMakeLists.txt` does `add_subdirectory(src)`, `add_subdirectory(bindings)`, and `add_subdirectory(ConfigurationManager)`; the executable is exactly `src/main.cpp` + the two imgui binding cpps, linking the `ConfigurationManager` static lib.

- `ConfigurationManager/` (JSON config singleton; includes `nlohmann/json.hpp` in its public header) is live — `src/main.cpp` uses it to resolve DB settings. Don't drop its `find_package(nlohmann_json)`; it must build standalone.
- `DBHandler/` (Core interfaces + Implementation + MariaDB impls) is **not** wired into the root build — no `add_subdirectory(DBHandler)`, nothing links it. Mostly skeleton/stub code. Don't assume it compiles or is used.
- `src/server.cpp` / `src/connection.cpp` / their headers are untouched Asio "http server3" tutorial copies that include headers that don't exist in the repo; they are not compiled into the executable.

## Testing

No test sources exist yet. CI has a `test` job (builds then `ctest`) but it runs **only on the `development` branch**; the `build` job runs on all branches. `git add` the stray `.github/worflows/ci.yml` (typo) — only `.github/workflows/ci.yml` is live.

## Style

`.clang-format`: LLVM base, 4-space indent, 80-col limit, Allman braces for functions/classes/control blocks, no bin-packing. `formatOnSave` is on via `BK-System.code-workspace`. ImGui/spdlog code follows the existing `draw_led_indicator` style.
