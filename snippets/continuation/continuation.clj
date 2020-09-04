(defn find-first-odd [coll success failure]
  (if (empty? coll)
    (failure)
    (let [first-element (first coll)]
      (if (odd? first-element)
        (success first-element)
        (find-first-odd (rest coll) success failure)))))

;; (find-first-odd [2 3 4] identity (constantly nil))
;; (find-first-odd [2 2 4] identity (constantly nil))

(defn collect-odd [coll collector]
  (if (empty? coll)
    (collector nil)
    (let [first-element (first coll)]
      (if (odd? first-element)
        (collect-odd (rest coll)
                     (fn [collected]
                       (collector (conj collected first-element))))
        (collect-odd (rest coll)
                     collector)))))

;; (collect-odd [1 2 3 4] identity)

(defn subseq-with-sum [total coll success failure]
  (if-let [match (first (filter #(= % total) coll))]
    (success [match])
    (let [candidates (filter #(< % total) coll)]
      (if (empty? candidates)
        (failure)
        (let [first-candidate (first candidates)]
          (subseq-with-sum
           (- total first-candidate) (rest candidates)
           (fn [collected]
             (success (conj collected first-candidate)))
           (fn []
             (subseq-with-sum total (rest candidates)
                              success failure))))))))


;; (subseq-with-sum 10 [1 2 5 6 7] identity (constantly nil))
;; (subseq-with-sum 10 [1 2 5] identity (constantly nil))
