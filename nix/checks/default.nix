{pkgs}: let
  format-checks = import ./format.nix {inherit pkgs;};
in
  {
    tests = import ./tests.nix {inherit pkgs;};
    build-debug = import ./build.nix {inherit pkgs;};
  }
  // format-checks
