import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;


public class Main {

    static String startFA(String automataInput, int max) {
        StringBuilder ret = new StringBuilder();
        StringBuilder input = new StringBuilder(automataInput);
        int i = 0;
        int strIndex = 0;
        State currState = null;
        char currChar;

        for(State x : states) {
            if(x.kind == 's') currState = x;
        }

        while(i < max) {
            if(currState.kind == 'a' || currState.kind == 'r') {
                if(currState.kind == 'a'){
                    ret.append(currState.num_state);
                    ret.append(" accept\n");
                } else{
                    ret.append(currState.num_state);
                    ret.append(" reject\n");
                }
                return ret.toString();
            }
            currChar = input.charAt(strIndex);

            Transition validT = null;

            for(Transition x : currState.objects) {
                if(x.read == currChar) validT = x;
            }

            //writing to string
            assert(strIndex >= 0 && strIndex <= input.length());
            input.setCharAt(strIndex, validT.write);


            //moving string
            if(validT.move == 'R') strIndex++;
            else strIndex--;

            ret.append(currState.num_state+"->");

            //updating state for next iteration
            for(State x : states) {
                if(x.num_state == validT.destination) currState = x;
            }
            i++;
        }
        ret.append(currState.num_state);
        ret.append(" quit\n");
        return ret.toString();
    }

    static ArrayList<State> states = new ArrayList<State>();
    static ArrayList<Transition> transitions = new ArrayList<Transition>();

    static class State{

        public State(int ns, char k) {
            this.num_state = ns;
            this.kind = k;
            this.objects = new ArrayList<Transition>();
        }

        public int num_state;
        public char kind;
        public ArrayList<Transition> objects;

    }

    static class Transition{

        public Transition(int s, char r, int d, char w, char m) {
            this.state = s;
            this.read = r;
            this.destination = d;
            this.write = w;
            this.move = m;
        }

        public int state;
        public char read;
        public int destination;
        public char write;
        public char move;

    }

    public static void main(String args[]) {
        if(args.length >= 0) {
            String inputFile = args[0];
            String automataInput = args[1];
            int maxTransitions = Integer.parseInt(args[2]);
            try {
                File input = new File(inputFile);
                Scanner reader = new Scanner(input);
                while(reader.hasNext()) {
                    if(reader.next().compareTo("state") == 0) {
                        String stateNum = reader.next();
                        String stateKind = reader.next();
                        states.add(new State(Integer.parseInt(stateNum), stateKind.toCharArray()[0]));
                    } else {
                        String fromState = reader.next();
                        String readChar = reader.next();
                        String toState = reader.next();
                        String writeChar = reader.next();
                        String indexMove = reader.next();
                        transitions.add(new Transition(Integer.parseInt(fromState), readChar.toCharArray()[0], Integer.parseInt(toState), writeChar.toCharArray()[0], indexMove.toCharArray()[0]));
                    }
                }
                reader.close();

                for(Transition x : transitions) {
                    boolean found = false;
                    Transition temp = null;
                    for(State y : states) {
                        temp = x;
                        if(y.num_state == x.state) {
                            found = true;
                            y.objects.add(x);
                        }
                    }
                    if(!found) {
                        states.add(new State(x.state, '0'));
                        states.get(states.size() - 1).objects.add(temp);
                    }
                }

            } catch (FileNotFoundException e) {
                System.out.println("Error opening input file");
            }

            String ret = startFA(automataInput, maxTransitions);
            System.out.println(ret);
        }
    }
}