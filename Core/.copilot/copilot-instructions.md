```instructions
# Core - LLM Instructions

Short summary:
- Core is a portable C++17 library (ECS, systems, managers) that is built independently.
- It provides headers under `include/` and produces a runtime library under `build/`.
- Consumers are expected to copy the headers and library into their project (or provide paths via CMake variables).

Developer notes for LLMs:
- Do not add system-wide install steps—Core is intentionally portable.
- Keep third-party dependency retrieval localized (see `cmake/ThirdParty.cmake`).
- When making API changes, update README and consumer projects' build scripts.

```