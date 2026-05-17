{pkgs}:
pkgs.writeShellApplication {
  name = "docs-mike";
  runtimeInputs = [
    (pkgs.python3.withPackages (ps: [
      ps.mkdocs
      ps.mkdocs-material
      ps.mike
    ]))
  ];
  text = ''
    set -eu

    cd docs
    mike "$@"
  '';
}
