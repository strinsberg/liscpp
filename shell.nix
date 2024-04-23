{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {

  nativeBuildInputs = with pkgs; [
    cmake pkg-config gcc13 clang-tools_17 gdb valgrind
  ];

  buildInputs = with pkgs; [
    gtest
  ];
}

