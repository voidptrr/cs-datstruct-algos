{...}: {
  perSystem = {
    pkgs,
    config,
    ...
  }: {
    packages = import ./packages {inherit pkgs;};

    formatter = pkgs.alejandra;

    devShells.default = pkgs.mkShell {
      packages = [
        pkgs.gcc
        config.packages.bench-all
        config.packages.docs-build
        config.packages.docs-dev
        config.packages.format-all
        config.packages.format-check
        config.packages.test-all
        config.packages.code-check
      ];
    };
  };
}
