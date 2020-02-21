;; Line by line transformation from The Seasoned Schemer.

(defn new-table []
  (fn [key] (throw (Exception. "not found"))))

(defn extend-table [table key value]
  (fn [k]
    (if (= k key)
      value
      (table k))))

(let [table (new-table)]
  (let [table (extend-table table "key1" "value1")]
    (let [table (extend-table table "key2" "value2")]
      (table "key2"))))

(defn multi-extend-table [table & kvs]
  (if (<= 2 (count kvs))
    (let [k (first kvs) v (second kvs)]
      (apply multi-extend-table (extend-table table k v) (rest (rest kvs))))
    table))


((multi-extend-table (new-table) "1" "a" "2" "b" "3" "c") "5")
