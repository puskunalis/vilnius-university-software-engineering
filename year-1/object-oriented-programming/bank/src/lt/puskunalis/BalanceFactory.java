package lt.puskunalis;

/**
 * Creates Balance objects.
 */
public final class BalanceFactory
{
    private BalanceFactory() {}

    public static Account createAccount()
    {
        return new Account();
    }

    public static Balance createCreditCard(Account account)
    {
        return new CreditCard(account);
    }

    public static DebitCard createDebitCard(Account account)
    {
        return new DebitCard(account);
    }

    public static Client createClient(String name, int birthYear, String address)
    {
        return new Client(name, birthYear, address);
    }
}
