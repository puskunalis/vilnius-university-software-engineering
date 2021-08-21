package lt.puskunalis;

public class CreditCard extends Card
{
    public CreditCard(Account account)
    {
        super(account);
    }

    /**
     * Forcefully withdraws money.
     *
     * @param amount amount to withdraw
     * @return true
     */
    @Override
    public boolean withdraw(double amount)
    {
        this.getAccount().forceWithdraw(amount);
        return true;
    }
}
