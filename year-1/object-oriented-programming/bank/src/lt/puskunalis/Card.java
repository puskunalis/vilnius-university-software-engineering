package lt.puskunalis;

import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.Setter;

import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Random;

/**
 * Represents a bank card.
 */
@EqualsAndHashCode
@Getter
public abstract class Card implements Balance
{
    @Setter
    private Account account;

    private final String number;

    @Setter
    private int expirationYear;

    @Setter
    private int expirationMonth;

    private final int cvv;

    public Card(Account account)
    {
        this.account = account;

        this.number = NumberHelper.generateNumericString(16);

        Date date = new Date();
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date);

        this.expirationYear = calendar.get(Calendar.YEAR) + 5;
        this.expirationMonth = calendar.get(Calendar.MONTH);

        this.cvv = 100 + new Random().nextInt(900);
    }

    /**
     * Returns the associated bank account's balance.
     *
     * @return associated bank account's balance
     */
    @Override
    public double getBalance()
    {
        return this.getAccount().getBalance();
    }

    /**
     * Returns the associated bank account's transaction history.
     *
     * @return associated bank account's transaction history
     */
    @Override
    public List<String> getTransactionHistory()
    {
        return this.getAccount().getTransactionHistory();
    }

    /**
     * Deposits money into the associated bank account.
     *
     * @param amount amount to deposit
     */
    @Override
    public void deposit(double amount)
    {
        this.getAccount().deposit(amount);
    }

    /**
     * Withdraws money from the associated bank account.
     *
     * @param amount amount to withdraw
     * @return whether the withdraw operation was successful
     */
    @Override
    public abstract boolean withdraw(double amount);

    /**
     * Withdraws money, even if the balance is insufficient.
     *
     * @param amount amount to forcefully withdraw
     */
    @Override
    public void forceWithdraw(double amount)
    {
        this.getAccount().forceWithdraw(amount);
    }

    /**
     * Sends money to another balance.
     *
     * @param balance balance to send money to
     * @param amount amount to send
     * @return whether the operation was successful
     */
    @Override
    public boolean sendMoney(Balance balance, double amount)
    {
        return this.getAccount().sendMoney(balance, amount);
    }
}
