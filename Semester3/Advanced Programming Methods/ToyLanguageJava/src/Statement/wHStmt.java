package Statement;

import ADT.IHeap;
import ADT.MyIDictionary;
import ADT.PrgState;
import Expression.IExp;
import Exception.MyException;
import Type.RefType;
import Value.IValue;
import Value.RefValue;

import java.sql.Ref;

public class wHStmt implements IStmt{

    String var_name;
    IExp expression;

    public wHStmt(String var_name,IExp expression){
        this.var_name = var_name;
        this.expression = expression;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, IValue>symTbl = state.getSymTable() ;
        IHeap<Integer,IValue>hp = state.getHeap();
        if(!(symTbl.isVarDef(var_name)))
            throw new MyException("The variable is not defined in the symbol table!");
        IValue value = symTbl.<String>lookUp(var_name);
        if(!(value.getType() instanceof RefType))
            throw new MyException("The variable does not have the type RefType so it can't be allocated on the heap");

        RefValue refValue = (RefValue)value;
        IValue hpValue = hp.lookUp(refValue.getAdress());
        if(!(hp.isVarDef(refValue.getAdress())))
            throw new MyException("This adress is not on the heap!");
        IValue evaluation =  expression.eval(symTbl,hp);
        if(!(evaluation.getType().equals(hpValue.getType())))
            throw new MyException("The types do not match <3!");
        hp.update(refValue.getAdress(),evaluation);
        state.setHeap(hp);
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new wHStmt(var_name,expression);
    }

    @Override
    public String toString(){
        return "wH("+var_name+","+expression+")";
    }
}
