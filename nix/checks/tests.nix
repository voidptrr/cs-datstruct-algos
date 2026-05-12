{pkgs}:
pkgs.runCommand "build-all-targets-check" {
  src = ../../.;
  nativeBuildInputs = [
    pkgs.cmake
    pkgs.gcc
    pkgs.gnumake
  ];
} ''
  cp -r "$src" source
  chmod -R +w source
  cd source

  build_dir="build-check/release"
  mkdir -p "$build_dir"
  cmake -S . -B "$build_dir" -DCMAKE_BUILD_TYPE=Release
  cmake --build "$build_dir"
  ctest --test-dir "$build_dir" --output-on-failure

  mkdir -p "$out"
  touch "$out/passed"
''
