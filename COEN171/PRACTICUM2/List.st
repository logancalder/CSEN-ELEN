"A little class for the nodes in the linked list."

Object subclass: #Node .
Node instanceVariableNames: 'data link' .

Node extend [
    data [ ^data ]
    link [ ^link ]

    data: anObject [ data := anObject ]
    link: aNode [ link := aNode ]
]


"Here we subclass Collection to make a linked list class.  We don't
 implement all the methods required but it's a start.  We deliberately use
 a singly-linked list to illustrate different ways of doing control flow."

Collection subclass: #List .
List instanceVariableNames: 'first' .

List extend [
    addFirst: anObject [
		"Add an object as the first object in the list."
		first := (Node new data: anObject) link: first
    ]

    removeFirst [
	"Remove and answer the first object in the list.  Answer nil if the
	 list is empty (because 'data' will be nil by default)."

	| data |
	first ifNotNil: [ data := first data . first := first link ] .
	^data
    ]

    addLast: anObject [
	"Add an object as the last object in the list."

	| current |
	first
	    ifNil: [
		first := Node new data: anObject
	    ]

	    ifNotNil: [
		current := first .
		[ current link notNil ] whileTrue: [ current := current link ] .
		current link: (Node new data: anObject)
	    ]
    ]

    removeLast [
	"Remove and answer the last object in the list.  Answer nil if the
	 list is empty."

	| current fred |
	first ifNil: [ ^nil ] .

	current := first .
	[ current link notNil ] whileTrue: [ fred := current .
					     current := current link ] .
	fred ifNil: [ first := nil ] ifNotNil: [ fred link: nil ] .
	^current data
    ]

    do: aBlock [
	"Enumerate each object in the list, passing it to aBlock.  Note
	 that sending a block the 'value' message executes the block with
	 the given parameter."

	| current |
	current := first .
	[ current notNil ] whileTrue: [ aBlock value: current data .
					current := current link ]
    ]
]
