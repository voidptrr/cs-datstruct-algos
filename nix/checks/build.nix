{pkgs}:
pkgs.runCommand "build-debug-sanitized-check" {
  src = ../../.;
  nativeBuildInputs = [
    pkgs.gcc
    pkgs.coreutils
    pkgs.findutils
    pkgs.gnused
  ];
} ''
  cp -r "$src" source
  chmod -R +w source
  cd source

  export CFLAGS="-g3 -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address,undefined -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wstrict-prototypes"
  export ASAN_OPTIONS="detect_leaks=1:abort_on_error=1"
  export UBSAN_OPTIONS="print_stacktrace=1:halt_on_error=1"

  src_files="$(find src -type f -name '*.c' | sort)"

  if [ -n "$src_files" ]; then
    echo "Compiling all src/*.c with debug+sanitizer flags"
    while IFS= read -r src_file; do
      [ -z "$src_file" ] && continue
      obj_dir="build-debug-check/obj"
      mkdir -p "$obj_dir"
      obj_name="$(printf '%s' "$src_file" | sed 's#/#-#g').o"
      cc $CFLAGS -I src -c "$src_file" -o "$obj_dir/$obj_name"
    done <<EOF
  $src_files
  EOF
  else
    echo "No C source files found under src/. Skipping src compile check."
  fi

  mkdir -p "$out"
  touch "$out/passed"
''
