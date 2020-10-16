(ns equiv.core
  (:require [clojure.test :refer :all]
            [clojure.set]))

(defn class-of [classes x]
  (first (filter (fn [c] (contains? c x)) classes)))

(defn unify [classes relation]
  (let [has-common-element (partial some (set relation))
        matching-classes (filter has-common-element classes)
        merged (apply clojure.set/union (set relation) matching-classes)
        non-matching-classes (remove has-common-element classes)]
    (conj (set non-matching-classes) merged)))

(defn equivalence-classes [inputs]
  (reduce unify #{} inputs))

(deftest test-equiv-classes
  (is (= (equivalence-classes [[:a :a]]) #{#{:a}}))
  (is (= (equivalence-classes [[:a :a] [:b :b]]) #{#{:a} #{:b}}))
  (is (= (equivalence-classes [[:a :b] [:b :c]]) #{#{:a :b :c}}))
  (is (= (equivalence-classes [[:a :b] [:b :c] [:a :c]]) #{#{:a :b :c}}))
  (is (= (equivalence-classes [[:a :b] [:b :a]]) #{#{:a :b}}))
  (is (= (equivalence-classes [[:a :b] [:b :c] [:c :d]]) #{#{:a :b :c :d}}))
  (is (= (equivalence-classes [[:a :b] [:b :c] [:d :e]]) #{#{:a :b :c} #{:d :e}}))
  (is (= (equivalence-classes [[:a :b] [:c :d] [:b :c]]) #{#{:a :b :c :d}})))

(run-tests)
