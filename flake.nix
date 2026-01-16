{
  description = "Arduino/IoT Dev Environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }: let
    pkgs = nixpkgs.legacyPackages."x86_64-linux";
  in
  {
    devShells.x86_64-linux.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        arduino-cli
	minicom # serial monitoring
	(python3.withPackages (p: with p; [
	  pyserial # data processing
	]))
      ];
      shellHook = ''
        echo "Arduino CLI Env Ready"
      '';
    };
  };
}
