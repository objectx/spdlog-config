#! /usr/bin/env stack
-- stack --install-ghc runghc --package turtle

{-# LANGUAGE OverloadedStrings #-}

import System.Info (os)
-- import Data.Text (pack)
-- import Debug.Trace (trace)
import Turtle

parser::Parser (Bool)
parser = switch "full" 'F' "Perform full build"

main = do
    -- echo $ pack os
    full <- options "Configure & build" parser
    when (full) $ rmtree "BUILD"
    mktree "BUILD"
    cd "BUILD"
    (proc "cmake" (cmakeConfiguration "..") empty)
    .&&. (proc "cmake" ["--build", "."] empty)
  where
    cmakeConfiguration dir =
        case os of
            "darwin" -> ["-G", "Ninja", dir]
            "windows" -> ["-A", "x64", dir]
            "mingw32" -> ["-A", "x64", dir]
