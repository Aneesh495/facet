{-# OPTIONS --safe #-}

module Facet.IO.OBJ where

open import Data.List using (List; []; _∷_)
open import Data.Nat using (ℕ)
open import Facet.Core.Vec3

record OBJFace : Set where
  constructor objFace
  field
    v1Index : ℕ
    v2Index : ℕ
    v3Index : ℕ

record OBJModel : Set where
  constructor objModel
  field
    vertices : List Vec3
    faces    : List OBJFace
