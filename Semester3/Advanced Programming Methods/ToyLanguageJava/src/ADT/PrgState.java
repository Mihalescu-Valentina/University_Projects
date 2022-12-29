package ADT;

import Statement.IStmt;
import Value.IValue;
import Value.StringValue;
import Exception.MyException;

import java.io.BufferedReader;

public class PrgState {

    private int id;
    private static int globalId = 0;

    private MyIStack<IStmt> exeStack;

    private MyIDictionary<String, IValue> symTable;

    private MyIList<IValue> out;
    private IHeap<Integer, IValue> heap;
    private MyIFileTable<StringValue, BufferedReader> ftbl;

    public synchronized int setGlobalId(){
        globalId+=1;
        return globalId;
    }

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, IValue> symtbl, MyIList<IValue> ot, MyIFileTable<StringValue, BufferedReader> ftable, IHeap<Integer, IValue> h, IStmt prg) {
        exeStack = stk;
        symTable = symtbl;
        out = ot;
        ftbl = ftable;
        heap = h;
        this.exeStack.push(prg);
        this.id = setGlobalId();
    }





    public Boolean isNotCompleted() {
        return !this.exeStack.isEmpty();
    }

    public int getId() {
        return id;
    }

    public void setId(int id2) {
        id = id2;
    }

    public MyIStack<IStmt> getExeStack() {
        return exeStack;
    }

    public void setExeStack(MyIStack<IStmt> exeStack) {
        this.exeStack = exeStack;
    }

    public MyIDictionary<String, IValue> getSymTable() {
        return symTable;
    }

    public void setSymTable(MyIDictionary<String, IValue> symTable) {
        this.symTable = symTable;
    }

    public MyIList<IValue> getOut() {
        return out;
    }

    public void setOut(MyIList<IValue> out) {
        this.out = out;
    }

    public String toString() {
        return "Program with id: " + id + '\n' +
                "Exe Stack : " + exeStack.toString() + '\n' +
                "Sym Table : " + symTable.toString() + '\n' +
                "Output : " + out.toString() + '\n' +
                "File Table: " + ftbl.toString() + '\n' +
                "Heap: " + heap.toString();
    }

    public void setHeap(IHeap<Integer, IValue> h) {
        this.heap = h;
    }

    public IHeap<Integer, IValue> getHeap() {
        return this.heap;
    }

    public MyIFileTable<StringValue, BufferedReader> getFileTable() {
        return ftbl;
    }

    public void setFileTable(MyIFileTable<StringValue, BufferedReader> ftbl) {
        this.ftbl = ftbl;
    }

    public PrgState oneStep() throws MyException {
        if (this.exeStack.isEmpty()) throw new MyException("prgState stack is empty");
        IStmt crtStmt = this.exeStack.pop();
        return crtStmt.execute(this);
    }

}
