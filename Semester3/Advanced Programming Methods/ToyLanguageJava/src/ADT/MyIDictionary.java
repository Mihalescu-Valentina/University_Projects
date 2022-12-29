package ADT;

import java.util.HashMap;
import java.util.Map;

public interface MyIDictionary<K,V> {
    void put(K key,V value);
    boolean isVarDef(K key);
    V lookUp(K key);
    void update(K key,V value);

    String toString();
    HashMap<K,V> getContent();
    void setContent(HashMap<K,V>map2);




}
