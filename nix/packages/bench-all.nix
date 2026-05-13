{pkgs}:
pkgs.writeShellApplication {
  name = "bench-all";
  runtimeInputs = [
    pkgs.cmake
    pkgs.gcc
    pkgs.gnumake
  ];
  text = ''
    set -eu

    cmake -S . -B build/bench -DCMAKE_BUILD_TYPE=Release
    cmake --build build/bench
    cmake --build build/bench --target bench
  '';
}
