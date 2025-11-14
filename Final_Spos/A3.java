import java.util.*;

class A3 {

    static {
        System.loadLibrary("A3"); // Loads A3.dll at runtime
    }

    private native int add(int a, int b);
    private native int sub(int a, int b);
    private native int mul(int a, int b);
    private native int div(int a, int b);

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        A3 obj = new A3();

        System.out.print("Value of a: ");
        int a = sc.nextInt();
        System.out.print("Value of b: ");
        int b = sc.nextInt();

        while (true) {
            System.out.println("\n----- MAIN MENU -----");
            System.out.println("1 -> Addition");
            System.out.println("2 -> Subtraction");
            System.out.println("3 -> Multiplication");
            System.out.println("4 -> Division");
            System.out.println("5 -> Exit");
            System.out.print("Choose an option: ");
            int choice = sc.nextInt();

            switch (choice) {
                case 1: System.out.println("Result: " + obj.add(a, b)); break;
                case 2: System.out.println("Result: " + obj.sub(a, b)); break;
                case 3: System.out.println("Result: " + obj.mul(a, b)); break;
                case 4: System.out.println("Result: " + obj.div(a, b)); break;
                case 5: System.out.println("## END OF CODE"); System.exit(0);
                default: System.out.println("Please choose a valid option."); break;
            }
        }
    }
}
/*steps to run-
> javac B1.java
>javah -jni B1
 >gcc -I/usr/lib/jvm/java-7-openjdk-amd64/include -I/usr/lib/jvm/java-7-
openjdk-amd64/include/linux -o libB1.so -shared -fPIC B1.c
> java -Djava.library.path=. B1*/











// first run this before you are going to .c file == javac A3.java
//javac -h . A3.java


//command to run .java code = java -Djava.library.path=. A3
