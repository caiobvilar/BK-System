# Checkpoint: bk-system-conan-build-fix
Started: 2026-08-05
Last updated: 2026-08-06
Status: complete

## Goal
Build the BK-System C++ banking app (SDL2 + ImGui + MariaDB) on Fedora 44 with GCC 16 using Conan 2. Fixed missing system deps (SDL video/audio backends), Perl modules for autotools, and GCC 16's default C23 breaking mariadb-connector-c and gettext. gettext 0.26 build failure caused by glibc's C23 `_Generic` in headers was finally solved at the **project level** (no recipe edits).

## Constraint (user-enforced, 2026-08-06)
Do NOT alter downloaded libraries (conan cache) or OS-distro/dnf libraries. Only the project's own libraries/modules may be refactored/fixed. The earlier cache-recipe patches were reverted; gettext removed from cache.

## Root cause (confirmed)
glibc 2.40+ on GCC 16: defining `_GNU_SOURCE` forces `_ISOC23_SOURCE` (features.h:225-226) → `__GLIBC_USE (ISOC23)` = 1 → wchar.h:301 defines a `wmemchr` macro that expands to `_Generic(...)`. In C17 `_Generic` is not a keyword, so gnulib's own `wchar.h:856` declaration gets macro-substituted → `expected identifier or '(' before '_Generic'`. Same for bsearch/memchr/strchr/strrchr/strpbrk/strstr in stdlib.h/string.h. Removing `_GNU_SOURCE` breaks wcwidth/off64_t/strtold_l. `-D_LIBC` is forbidden by glibc.

## Final fix (project-level, ALLOWED)
gettext/1.0 (conancenter) builds cleanly from source with just `-std=gnu17` — its gnulib already handles glibc 2.40 C23 overload macros. It is forced via a **project-owned profile** because `tool_requires` are private (visible=False) and cannot be overridden from a downstream recipe (recipe-level `override=True` is silently ignored).

`conan_profiles/override_gettext`:
```ini
include(default)

[tool_requires]
pulseaudio/*: gettext/1.0
```

## Done
- [x] Created ConfigurationManager module from configuration-manager branch (CMakeLists, header, source)
- [x] Created config.json without secrets
- [x] Wired ConfigurationManager into root CMakeLists.txt and linked into executable
- [x] Refactored src/main.cpp to load config via ConfigurationManager with env precedence (env > config.json > default), password env-only
- [x] Updated AGENTS.md to reflect ConfigurationManager wiring and config.json, and fixed preset name to `conan-release`
- [x] Installed Conan 2.31.2 via pip
- [x] Installed 43 system packages via dnf with sudo -A (mesa-libEGL-devel, libglvnd-devel, X11/Wayland dev, perl-threads, etc.)
- [x] Added `-c tools.build:cflags="[-std=gnu17]"` to fix mariadb-connector-c C23 typedef bool error
- [x] Determined gettext root cause: `_GNU_SOURCE` → `_ISOC23_SOURCE` → `_Generic` overload macros corrupt gnulib declarations in C17
- [x] Tried & discarded recipe-level fixes (config.h XOPEN_SOURCE broke off64_t/strtold_l; -D_LIBC forbidden; .in.h #undef worked but is a recipe edit → reverted per constraint)
- [x] Reverted gettext recipe to pristine; `conan remove "gettext/0.26*" -c`; wiped all patched gette* build folders
- [x] Fixed global AGENTS.md: `SSH_ASKPASS` → `SUDO_ASKPASS` (line 8)
- [x] Created debrief.md cataloguing all mishaps/bugs/errors/fixes/decisions
- [x] Verified gettext/1.0 builds cleanly standalone (no recipe edits)
- [x] Added project profile `conan_profiles/override_gettext`; verified via `conan graph info` that pulseaudio resolves gettext/1.0
- [x] FULL INSTALL SUCCESS: `conan install . -pr:h=conan_profiles/override_gettext -pr:b=conan_profiles/override_gettext --build=missing -c tools.build:cflags="[\"-std=gnu17\"]"` — all 43 packages, 0 errors (log: /tmp/opencode/conan_install_v11.log)
- [x] CMake configure + build success: `cmake --preset conan-release && cmake --build --preset conan-release` → build/Release/BK-System (13.3 MB, 0 missing libs)
- [x] Smoke test: binary runs, loads config.json, correctly refuses to start without BKSYS_DB_PASSWORD

## Next step (optional, only when a DB is available)
Set BKSYS_DB_HOST/USER/PASSWORD and run the binary for a full GUI session.

## State snapshot
- Project: /home/hellscoffe/Development/BK-System
- Built binary: build/Release/BK-System (full SDL backends, no trims)
- Project profile: conan_profiles/override_gettext
- gettext cache: pristine; gettext/1.0 built from conancenter source with -std=gnu17
- Logs: /tmp/opencode/conan_install_v11.log (success), final5-10.log (failure archaeology)
- debrief.md at repo root documents everything

## Log
- 2026-08-05 15:30 — Created AGENTS.md for repo with build/runtime/build-scope/style guidance
- 2026-08-05 15:45 — Added ConfigurationManager module from configuration-manager branch
- 2026-08-05 16:00 — Refactored main.cpp, updated CMakeLists, config.json, AGENTS.md
- 2026-08-05 17:00 — Installed Conan, started build attempts
- 2026-08-05 18:00 — Hit SDL system deps; installed 43 packages via dnf with sudo askpass
- 2026-08-05 19:00 — Fixed perl threads, mariadb C23 issue; gettext fails on C23
- 2026-08-06 — Deep-dived gettext _Generic root cause; found & tested .in.h #undef recipe fix (worked); USER imposed "no downloaded-library edits" constraint → reverted everything
- 2026-08-06 11:43 — Project-level fix via gettext/1.0 + profile [tool_requires] override; full install + build SUCCESS; binary smoke-tested
