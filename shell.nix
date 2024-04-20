{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {

  nativeBuildInputs = with pkgs; [
    cmake pkg-config gcc clang-tools
  ];

  buildInputs = with pkgs; [
    gtest
  ];

}

