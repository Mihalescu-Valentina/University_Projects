package ADT;

import Value.IValue;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public interface IHeap<K,V>{
    String toString();
    int put(V value);
    boolean isVarDef(K key);
    V lookUp(K key);
    void update(K key,V value);

    void setContent(HashMap<Integer, IValue> map);
    HashMap<Integer,IValue>getContent();
    int getFreeLocation();
}
