package Statement;

import ADT.IHeap;
import ADT.MyIDictionary;
import ADT.MyIStack;
import ADT.PrgState;
import Expression.IExp;
import Exception.MyException;
import Type.IType;
import Value.IValue;
import Exception.MyException;

public class AssignStmt implements IStmt{
    IExp exp;
    String id;

    public AssignStmt(IExp exp, String id) {
        this.exp = exp;
        this.id = id;
    }

    @Override
    public String toString(){ return id+"="+ exp.toString();}

    @Override
    public IStmt deepCopy(){
        return new AssignStmt(exp.deepCopy(),new String(id));
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {

        MyIStack<IStmt>stack = state.getExeStack();
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        IHeap<Integer,IValue>hp = state.getHeap();
        if(symTbl.isVarDef(id)){
            IValue val = exp.eval(symTbl,hp);
            IType typId= (symTbl.lookUp(id)).getType();
            if (val.getType().equals(typId))
                symTbl.update(id, val);
            else
                throw new MyException("The types of the lhso and rhso do not match!");

        }


            else
                throw new MyException("the used variable" +id + " was not declared before");
            return null;

        //posibil sa fi pus gresit parantezele

    }

}
