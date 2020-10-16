(ns with-loom.core
  (:require
   [clojure.test :refer :all]
   [loom.graph]
   [loom.alg]))

(defn equivalence-classes [inputs]
  (set (map set (loom.alg/connected-components (apply loom.graph/graph inputs)))))

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
