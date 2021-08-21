package lt.puskunalis;

import lombok.EqualsAndHashCode;
import lombok.Getter;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a single bank account.
 */
@EqualsAndHashCode
@Getter
public class Account implements Balance
{
    private final String number;

    private final List<String> transactionHistory;

    private double balance;

    public Account()
    {
        this.number = "LT" + NumberHelper.generateNumericString(18);
        this.transactionHistory = new ArrayList<>();
        this.balance = 0;
    }

    /**
     * Deposits money into the account.
     *
     * @param amount amount to deposit
     */
    @Override
    public void deposit(double amount)
    {
        if (amount > 0)
        {
            this.balance += amount;
            this.getTransactionHistory().add(String.format("Deposited %.2f to account %s.", amount, this.getNumber()));
        }
    }

    /**
     * Withdraws money from the account if the balance is sufficient.
     *
     * @param amount amount to deposit
     * @return was withdraw operation successful
     */
    @Override
    public boolean withdraw(double amount)
    {
        if (amount > 0 && this.getBalance() >= amount)
        {
            this.balance -= amount;
            this.getTransactionHistory().add(String.format("Withdrawn %.2f from account %s.", amount, this.getNumber()));

            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Withdraws money from the account, even if the balance is insufficient.
     *
     * @param amount amount to forcefully withdraw
     */
    public void forceWithdraw(double amount)
    {
        if (amount > 0)
        {
            this.balance -= amount;
            this.getTransactionHistory().add(String.format("Forcefully withdrawn %.2f from account %s.", amount, this.getNumber()));
        }
    }

    /**
     * Sends money to another balance.
     *
     * @param balance balance to send money to
     * @param amount amount to send
     * @return was transfer operation successful
     */
    public boolean sendMoney(Balance balance, double amount)
    {
        if (amount > 0 && this.getBalance() >= amount)
        {
            this.balance -= amount;
            balance.deposit(amount);
            balance.getTransactionHistory().remove(balance.getTransactionHistory().size() - 1);

            this.getTransactionHistory().add(String.format("Sent %.2f from account %s to account %s.", amount, this.getNumber(), balance.getNumber()));
            balance.getTransactionHistory().add(String.format("Received %.2f from account %s to account %s.", amount, this.getNumber(), balance.getNumber()));

            return true;
        }
        else
        {
            return false;
        }
    }
}
