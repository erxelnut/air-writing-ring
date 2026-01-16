{
  description = "Arduino/IoT Dev Environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }: let
    pkgs = nixpkgs.legacyPackages."x86_64-linux";
  in
  {
    devShells.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        arduino-cli
	python3 #data processing
	python3Packages.pyserial
	minicom # serial monitoring
      ];
      shellHook = ''
        echo "Arduino CLI Env Ready"
      '';
    }
  };
}
