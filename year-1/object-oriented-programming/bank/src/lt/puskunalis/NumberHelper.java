package lt.puskunalis;

import java.util.HashSet;
import java.util.Random;
import java.util.Set;

/**
 * Used to generate strings of numbers for bank accounts and cards.
 */
public class NumberHelper
{
    private static final Set<String> usedStrings = new HashSet<>();

    /**
     * Returns a unique string of random numbers.
     *
     * @param length length of string to return
     * @return string with random numbers
     */
    public static String generateNumericString(int length)
    {
        if (length <= 0 || NumberHelper.countUsedStrings(length) == (int) Math.pow(10, length))
        {
            return "";
        }

        StringBuilder sb = new StringBuilder();
        Random random = new Random();

        for (int i = 0; i < length; ++i)
        {
            sb.append(random.nextInt(10));
        }

        String randomString = sb.toString();

        if (usedStrings.contains(randomString))
        {
            return NumberHelper.generateNumericString(length);
        }
        else
        {
            usedStrings.add(randomString);
            return randomString;
        }
    }

    /**
     * Returns the number of already created strings of given length.
     *
     * @param length length of strings to check
     * @return number of used strings with that length
     */
    private static int countUsedStrings(int length)
    {
        int numberOfStrings = 0;

        for (String string : NumberHelper.usedStrings)
        {
            if (string.length() == length)
            {
                ++numberOfStrings;
            }
        }

        return numberOfStrings;
    }
}
