package Repository;

import ADT.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import Exception.MyException;

public class Repository implements IRepository {
    List<PrgState> repository;
    public String logFilePath = "";




    public Repository(PrgState prg, String logFilePath) {
        this.repository = new ArrayList<>();
        this.logFilePath = logFilePath;
        repository.add(prg);
    }


    @Override
    public void logPrgStateExec(PrgState prgSt) throws MyException {
        try {
            PrintWriter logFile;
            logFile =  new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.write(prgSt.toString());
            logFile.write("\n");
            logFile.flush();
        } catch (IOException e) {
            throw new MyException("error" + e);

        }
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.repository;
    }

    @Override
    public void setPrgList(List<PrgState> prgStates) {
        this.repository = prgStates;
    }
}
