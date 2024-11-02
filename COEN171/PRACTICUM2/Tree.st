"Name: Logan Calder"
"Class: CSEN 171 MWF 9:15"
"Homework 2: Binary Search Tree in Smalltalk"
"Description: This file is a conversion of Tree.h, which contains instance methods for classes Node and Tree, which implement a BST.
              This file also contains a maximum method, which returns the greatest value in the BST."

Object subclass: #Node .
Node instanceVariableNames: 'data left right' .

Node extend [
    data: anObject [
        data := anObject
    ]

    member: anObject [
        anObject < data
            ifTrue: [left ifNil: [^false] ifNotNil: [^left member: anObject]] .
        anObject > data
            ifTrue: [right ifNil: [^false] ifNotNil: [^right member: anObject]] .
        ^true
    ]

    insert: anObject [
        anObject < data
            ifTrue: [left ifNil: [left := (Node new) data: anObject] ifNotNil: [left insert: anObject]] .
        anObject > data
            ifTrue: [right ifNil: [right := (Node new) data: anObject] ifNotNil: [right insert: anObject]] .
    ]

    maxNode [
        right ifNil: [^data] ifNotNil: [^right maxNode]
    ]
]

Object subclass: #Tree .
Tree instanceVariableNames: 'root' .

Tree extend [
    member: anObject [
        root ifNil: [^false] ifNotNil: [^root member: anObject]
    ]

    insert: anObject [
        root ifNil: [root := (Node new) data: anObject]
             ifNotNil: [root insert: anObject]
    ]

    maximum [
        root ifNil: [^nil] ifNotNil: [^root maxNode]
    ]
]