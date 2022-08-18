#pragma once

#define arg_str(name) char* name = NULL; for (int i = 1; i < argc; i++) { if (strcmp(argv[i], "--"#name) == 0) { name = argv[i + 1]; break; } }
#define arg(name) bool name = false; for (int i = 1; i < argc; i++) { if (strcmp(argv[i], "--"#name) == 0) { name = true; break; } }