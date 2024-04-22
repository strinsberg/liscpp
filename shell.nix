{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {

  nativeBuildInputs = with pkgs; [
    cmake pkg-config gcc13 clang-tools_17
  ];

  buildInputs = with pkgs; [
    gtest
  ];
}

