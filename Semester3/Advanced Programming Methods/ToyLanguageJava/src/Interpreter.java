import ADT.*;
import Controller.Controller;
import Expression.*;
import Repository.IRepository;
import Repository.Repository;
import Statement.*;
import Type.BoolType;
import Type.IntType;
import Type.RefType;
import Type.StringType;
import Value.BoolValue;
import Value.IValue;
import Value.IntValue;
import Value.StringValue;
import View.RunExample;
import View.TextMenu;
import View.ExitCommand;

import java.io.BufferedReader;

class Interpreter {
    public static void main(String[] args) {
        IStmt ex1 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(
                                        new NewStmt("a", new VarExp("v")),
                                        new CompStmt(
                                                new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a"))
                                        )
                                )
                        )
                )
        );

        MyIStack<IStmt> stack1 = new MyStack<IStmt>();
        MyIList<IValue> out1 = new MyList<IValue>();
        MyIDictionary<String, IValue> symTbl1 = new MyDictionary<String, IValue>();
        MyIFileTable<StringValue, BufferedReader> ftbl1 = new MyFileTable<StringValue, BufferedReader>();
        IHeap<Integer, IValue> hp1 = new Heap();
        PrgState prg1 = new PrgState(stack1, symTbl1, out1, ftbl1, hp1, ex1);
        IRepository repo1 = new Repository(prg1, "log1.txt");
        Controller ctr1 = new Controller(repo1);


        IStmt ex2 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(
                                        new NewStmt("a", new VarExp("v")),
                                        new CompStmt(
                                                new PrintStmt(new rHExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp(
                                                        new rHExp(new rHExp(new VarExp("a"))),
                                                        new ValueExp(new IntValue(5)),
                                                        1)
                                                )
                                        )
                                )
                        )
                )
        );
        MyIStack<IStmt> stack2 = new MyStack<IStmt>();
        MyIList<IValue> out2 = new MyList<IValue>();
        MyIDictionary<String, IValue> symTbl2 = new MyDictionary<String, IValue>();
        MyIFileTable<StringValue, BufferedReader> ftbl2 = new MyFileTable<StringValue, BufferedReader>();
        IHeap<Integer, IValue> hp2 = new Heap();
        PrgState prg2 = new PrgState(stack2, symTbl2, out2, ftbl2, hp2, ex2);
        IRepository repo2 = new Repository(prg2, "log2.txt");
        Controller ctr2 = new Controller(repo2);
        IStmt ex3 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new PrintStmt(new rHExp(new VarExp("v"))),
                                new CompStmt(
                                        new wHStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp(
                                                new rHExp(new VarExp("v")),
                                                new ValueExp(new IntValue(5)),
                                                1)
                                        )
                                )
                        )
                )
        );
        MyIStack<IStmt> stack3 = new MyStack<IStmt>();
        MyIList<IValue> out3 = new MyList<IValue>();
        MyIDictionary<String, IValue> symTbl3 = new MyDictionary<String, IValue>();
        MyIFileTable<StringValue, BufferedReader> ftbl3 = new MyFileTable<StringValue, BufferedReader>();
        IHeap<Integer, IValue> hp3 = new Heap();
        PrgState prg3 = new PrgState(stack3, symTbl3, out3, ftbl3, hp3, ex3);
        IRepository repo3 = new Repository(prg3, "log3.txt");
        Controller ctr3 = new Controller(repo3);


        IStmt ex4 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(
                                        new NewStmt("a", new VarExp("v")),
                                        new CompStmt(
                                                new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new rHExp(new rHExp(new VarExp("a"))))
                                        )
                                )
                        )
                )
        );
        MyIStack<IStmt> stack4 = new MyStack<IStmt>();
        MyIList<IValue> out4 = new MyList<IValue>();
        MyIDictionary<String, IValue> symTbl4 = new MyDictionary<String, IValue>();
        MyIFileTable<StringValue, BufferedReader> ftbl4 = new MyFileTable<StringValue, BufferedReader>();
        IHeap<Integer, IValue> hp4 = new Heap();
        PrgState prg4 = new PrgState(stack4, symTbl4, out4, ftbl4, hp4, ex4);
        IRepository repo4 = new Repository(prg4, "log4.txt");
        Controller ctrl4 = new Controller(repo4);


        IStmt ex5 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new AssignStmt(new ValueExp(new IntValue(4)), "v"),
                        new CompStmt(
                                new whileStmt(
                                        new RelationalExp(
                                                new VarExp("v"),
                                                new ValueExp(new IntValue(0)),
                                                5
                                        ),
                                        new CompStmt(
                                                new PrintStmt(new VarExp("v")),
                                                new AssignStmt(new ArithExp(
                                                        new VarExp("v"),
                                                        new ValueExp(new IntValue(1)),
                                                        2), "v"
                                                )
                                        )
                                ),
                                new PrintStmt(new VarExp("v"))
                        )
                )
        );
        MyIStack<IStmt> stack5 = new MyStack<IStmt>();
        MyIList<IValue> out5 = new MyList<IValue>();
        MyIDictionary<String, IValue> symTbl5 = new MyDictionary<String, IValue>();
        MyIFileTable<StringValue, BufferedReader> ftbl5 = new MyFileTable<StringValue, BufferedReader>();
        IHeap<Integer, IValue> hp5 = new Heap();
        PrgState prg5 = new PrgState(stack5, symTbl5, out5, ftbl5, hp5, ex5);
        IRepository repo5 = new Repository(prg5, "log5.txt");
        Controller ctrl5 = new Controller(repo5);

        IStmt ex6 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt(new ValueExp(new IntValue(10)), "v"),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),new CompStmt(
                                        new forkStmt(new CompStmt(new wHStmt("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt(new ValueExp(new IntValue(32)), "v"),
                                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                                new PrintStmt(new rHExp(new VarExp("a")))
                                                        )))),new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new rHExp(new VarExp("a"))))
                                        )

                                ))

                ));


        MyIStack<IStmt> stack6 = new MyStack<IStmt>();
        MyIList<IValue> out6 = new MyList<IValue>();
        MyIDictionary<String, IValue> symTbl6 = new MyDictionary<String, IValue>();
        MyIFileTable<StringValue, BufferedReader> ftbl6 = new MyFileTable<StringValue, BufferedReader>();
        IHeap<Integer, IValue> hp6 = new Heap();
        PrgState prg6 = new PrgState(stack6, symTbl6, out6, ftbl6, hp6, ex6);
        IRepository repo6 = new Repository(prg6, "log6.txt");
        Controller ctrl6 = new Controller(repo6);


        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
        menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
        menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
        menu.addCommand(new RunExample("4", ex4.toString(), ctrl4));
        menu.addCommand(new RunExample("5", ex5.toString(), ctrl5));
        menu.addCommand(new RunExample("6", ex6.toString(), ctrl6));
        menu.show();
    }
}