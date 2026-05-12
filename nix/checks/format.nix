{pkgs}: {
  format-nix =
    pkgs.runCommand "format-nix-check" {
      src = ../../.;
      nativeBuildInputs = [
        pkgs.alejandra
        pkgs.coreutils
      ];
    } ''
      cp -r "$src" source
      chmod -R +w source
      cd source

      alejandra --check .

      mkdir -p "$out"
      touch "$out/passed"
    '';

  format-c =
    pkgs.runCommand "format-c-check" {
      src = ../../.;
      nativeBuildInputs = [
        pkgs.clang-tools
        pkgs.coreutils
        pkgs.findutils
      ];
    } ''
      cp -r "$src" source
      chmod -R +w source
      cd source

      files="$(find src tests -type f \( -name '*.c' -o -name '*.h' \) | sort)"

      if [ -z "$files" ]; then
        echo "No C files found under src/ or tests/. Skipping C format check."
        mkdir -p "$out"
        touch "$out/passed"
        exit 0
      fi

      while IFS= read -r file; do
        [ -z "$file" ] && continue
        clang-format --dry-run --Werror "$file"
      done <<EOF
      $files
      EOF

      mkdir -p "$out"
      touch "$out/passed"
    '';
}
