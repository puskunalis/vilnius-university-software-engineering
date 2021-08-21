import java.util.Scanner;

public class Main
{
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args)
    {
        String name = getName();
        greetUser(name);
        
        int month = getMonth();
        printSeason(month);
    }

    private static void greetUser(String name)
    {
        String greetingName = getGreetingName(name);
        System.out.println("Sveiki, " + greetingName);
    }

    private static String getName()
    {
        System.out.println("Įveskite savo vardą:");
        return scanner.nextLine().trim();
    }
    
    private static String getGreetingName(String name)
    {
        if (name.endsWith("ius") || name.endsWith("jus"))
        {
            return name.substring(0, name.length() - 2) + "au";
        }
        else if (name.endsWith("as"))
        {
            return name.substring(0, name.length() - 1) + "i";
        }
        else if (name.endsWith("is") || name.endsWith("ys"))
        {
            return name.substring(0, name.length() - 1);
        }
        else if (name.endsWith("ė"))
        {
            return name.substring(0, name.length() - 1) + "e";
        }
        else
        {
            return name;
        }
    }

    private static int getMonth()
    {
        String[] months = {"saus", "vasar", "kov", "baland", "gegu", "bir", "liep", "rugpj", "rugs", "spal", "lapkr", "gruod"};

        while (true)
        {
            System.out.println("Įveskite savo gimimo mėnesį:");
            String birthMonth = scanner.nextLine().trim().toLowerCase();

            try
            {
                int month = Integer.parseInt(birthMonth);

                if (month >= 1 && month <= 12)
                {
                    return month;
                }
            }
            catch (NumberFormatException e)
            {
                for (int i = 0; i < months.length; ++i)
                {
                    if (birthMonth.startsWith(months[i]))
                    {
                        return i + 1;
                    }
                }
            }
        }
    }

    private static void printSeason(int month)
    {
        switch (month)
        {
            case 12:
            case 1:
            case 2:
                System.out.println("Jūs gimęs žiemą.");
                break;
            case 3:
            case 4:
            case 5:
                System.out.println("Jūs gimęs pavasarį.");
                break;
            case 6:
            case 7:
            case 8:
                System.out.println("Jūs gimęs vasarą.");
                break;
            case 9:
            case 10:
            case 11:
                System.out.println("Jūs gimęs rudenį.");
                break;
            default:
                break;
        }
    }
}
