(ns equiv.core
  (:require [clojure.test :refer :all]
            [clojure.set]))

(defn equivalence-classes [inputs]
  (let [relatives (fn [h x]
                    (clojure.set/union
                     #{x}
                     (ancestors h x)
                     (descendants h x)))
        hierarchy (reduce (fn [hierarchy [x y]]
                            (if (or (= x y) (contains? (relatives hierarchy x) y))
                              hierarchy
                              (apply derive hierarchy (sort [x y]))))
                          (make-hierarchy)
                          inputs)]

    (set (map (partial relatives hierarchy) (apply concat inputs)))))

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
