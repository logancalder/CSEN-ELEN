// Name: Logan Calder
// Date: 10/12/2024
// Title: Practicum 1 – 2.1: BST (Pascal)

program bst (input, output);
    type tree = ^node;
    node = record
            data : integer;
            left, right : tree
    end;
    procedure insert(var root : tree; value : integer);
    begin
            if root = nil then
                begin
                        new(root);
                        root^.left := nil;
                        root^.right := nil;
                        root^.data := value;
                end
            else if value < root^.data then
                    insert(root^.left, value)
            else if value > root^.data then
                    insert(root^.right, value)
    end;

    function member(root : tree; value : integer) : boolean;
    begin
        if root = nil then
            member := false
        else if value < root^.data then
            member := member(root^.left, value)
        else if value > root^.data then
            member := member(root^.right, value)
        else
            member := true
    end;

    procedure maximum(root : tree);
    begin
        if root = nil then
            writeln('empty tree');
        while root^.right <> nil do
            root := root^.right;
        writeln('Maximum: ', root^.data)

    end;

    var t : tree;
        x : integer;

    procedure delete(var root: tree);
    begin
        if root = nil then
            writeln('empty tree')
        else
            delete(root^.left);
            delete(root^.right);
            dispose(root)
    end;

begin
    t := nil;
    read(x);

    while x <> -1 do
    begin
            insert(t,x);
            read(x)
    end;

    read(x);
    while x <> -1 do
        begin
            writeln(member(t,x));
            read(x);
        end;
    maximum(t);
    delete(t);
end.