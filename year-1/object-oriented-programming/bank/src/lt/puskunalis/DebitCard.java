package lt.puskunalis;

public class DebitCard extends Card
{
    public DebitCard(Account account)
    {
        super(account);
    }

    /**
     * Withdraws money if the balance is sufficient.
     *
     * @param amount amount to withdraw
     * @return was withdraw operation successful
     */
    @Override
    public boolean withdraw(double amount)
    {
        return this.getAccount().withdraw(amount);
    }
}
