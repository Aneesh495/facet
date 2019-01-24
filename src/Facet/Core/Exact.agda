{-# OPTIONS --safe #-}

module Facet.Core.Exact where

open import Data.Nat using (ℕ; zero; suc; _+_; _*_)
open import Data.Integer using (ℤ; +_; -[1+_]; _+_; _*_) renaming (-_ to -ℤ_)
open import Data.Bool using (Bool; true; false; if_then_else_)
open import Relation.Binary.PropositionalEquality using (_≡_; refl)

record Rat : Set where
  constructor _/_
  field
    num : ℤ
    den : ℕ

rat : ℤ → ℕ → Rat
rat n d = n / d

ratZero : Rat
ratZero = (+ 0) / 0

ratOne : Rat
ratOne = (+ 1) / 0

ratTwo : Rat
ratTwo = (+ 2) / 0

ratHalf : Rat
ratHalf = (+ 1) / 1

infix 8 -ᵣ_
-ᵣ_ : Rat → Rat
-ᵣ (n / d) = (-ℤ n) / d

infixl 6 _+ᵣ_ _-ᵣ_
infixl 7 _*ᵣ_

_+ᵣ_ : Rat → Rat → Rat
(n₁ / d₁) +ᵣ (n₂ / d₂) =
  let d1-val = suc d₁
      d2-val = suc d₂
      num-res = (n₁ Data.Integer.* (+ d2-val)) Data.Integer.+ (n₂ Data.Integer.* (+ d1-val))
      den-val = (d1-val Data.Nat.* d2-val)
  in case den-val of λ
    { zero → (+ 0) / 0
    ; (suc k) → num-res / k
    }
  where
    case_of_ : ∀ {a b} {A : Set a} {B : Set b} → A → (A → B) → B
    case x of f = f x

_-ᵣ_ : Rat → Rat → Rat
r₁ -ᵣ r₂ = r₁ +ᵣ (-ᵣ r₂)

_*ᵣ_ : Rat → Rat → Rat
(n₁ / d₁) *ᵣ (n₂ / d₂) =
  let d1-val = suc d₁
      d2-val = suc d₂
      num-res = n₁ Data.Integer.* n₂
      den-val = d1-val Data.Nat.* d2-val
  in case den-val of λ
    { zero → (+ 0) / 0
    ; (suc k) → num-res / k
    }
  where
    case_of_ : ∀ {a b} {A : Set a} {B : Set b} → A → (A → B) → B
    case x of f = f x

isPositive : Rat → Bool
isPositive (n / d) = case n of λ
  { (+ suc _) → true
  ; _ → false
  }
  where
    case_of_ : ∀ {a b} {A : Set a} {B : Set b} → A → (A → B) → B
    case x of f = f x

isZero : Rat → Bool
isZero (n / d) = case n of λ
  { (+ 0) → true
  ; _ → false
  }
  where
    case_of_ : ∀ {a b} {A : Set a} {B : Set b} → A → (A → B) → B
    case x of f = f x

isNegative : Rat → Bool
isNegative (n / d) = case n of λ
  { -[1+ _ ] → true
  ; _ → false
  }
  where
    case_of_ : ∀ {a b} {A : Set a} {B : Set b} → A → (A → B) → B
    case x of f = f x

det2x2 : Rat → Rat → Rat → Rat → Rat
det2x2 a b c d = (a *ᵣ d) -ᵣ (b *ᵣ c)

det3x3 : Rat → Rat → Rat →
         Rat → Rat → Rat →
         Rat → Rat → Rat → Rat
det3x3 a b c d e f g h i =
  ((a *ᵣ det2x2 e f h i) -ᵣ (b *ᵣ det2x2 d f g i)) +ᵣ (c *ᵣ det2x2 d e g h)
