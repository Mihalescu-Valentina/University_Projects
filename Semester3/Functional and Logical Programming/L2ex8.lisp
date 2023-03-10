(defun nrNodes (tree level k)
  (cond
     ((and (atom tree) (= level k)) 1)
     ((atom tree) 0)
     (t (apply #'+(mapcar #'(lambda (a)(nrNodes a (+ 1 level) k)) tree))) 

)
)

(defun nodesLevelK (tree level k)
  (cond
    ((and(atom tree)(= level k)) (list tree))
    ((atom tree) nil)
    (t (mapcan #'(lambda (a) (nodesLevelK a (+ 1 level) k)) tree))
)
)


(defun mainNodesLevelK(tree k)
  (nodesLevelK tree -1 k)
)

(defun prinF()
(print (mainNodesLevelK '(a(b(d(g)(h)) (e(i))) (c(f(j(l)) (k)))) 2 )

))


(defun testMainNodesLevelK()
  
    (assert
       (and
          (equal '(D E F) (mainNodesLevelK '(a(b(d(g)(h)) (e(i))) (c(f(j(l))(k)))) 2))
          (equal '(G H I J K) (mainNodesLevelK '(a(b(d(g)(h)) (e(i))) (c(f(j(l))  (k)))) 3))

)
))


(defun mainNrNodes(tree k)
 (nrNodes tree -1 k)
)

(defun testMainNrNodes()
(assert
(and
(equal 3 (mainNrNodes'(a(b(c)) (d)(e(f))) 1))
(equal 5 (mainNrNodes '(a(b(d(g)(h)) (e(i))) (c(f(j(l)) (k))))3))
(equal 2 (mainNrNodes '(a(b(d(g)(h)) (e(i))) (c(f(j(l)) (k)))) 1))
)
)
)
; nrNodes(tree level k) = {
;	- 1 if tree us an atom and level = k
;       - 0 if tree is an atom
;	- sum(i=1;i<=n;i++) of nrNodes(tree[i],level+1,k) otherwise
;}

