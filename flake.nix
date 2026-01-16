{
  description = "Arduino/IoT Dev Environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }: let
    pkgs = import nixpkgs {
      system = "x86_64-linux";
      config = {
        allowUnfree = true;
	# Allow the insecure dependency required by adafruit-nrfutil
        permittedInsecurePackages = [
          "python3.13-ecdsa-0.19.1"
        ];
	};
      };
  in
  {
    devShells.x86_64-linux.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        arduino-cli
	minicom # serial monitoring
	(python3.withPackages (p: with p; [
	  pyserial # data processing
	]))
	adafruit-nrfutil
      ];
      shellHook = ''
        echo "Arduino CLI Env Ready"
      '';
    };
  };
}
