package lt.puskunalis;

import lombok.EqualsAndHashCode;
import lombok.Getter;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Represents a client of the bank.
 */
@EqualsAndHashCode(callSuper = true)
@Getter
public class Client extends Person implements Balance
{
    private final Set<Account> accounts;

    private Account mainAccount;

    public Client(String name, int birthYear, String address)
    {
        super(name, birthYear, address);
        this.accounts = new HashSet<>();
    }

    /**
     * Assigns a bank account to this client.
     *
     * @param account bank account to assign to this client
     */
    public void addAccount(Account account)
    {
        if (account != null)
        {
            this.accounts.add(account);

            if (this.getMainAccount() == null)
            {
                this.setMainAccount(account);
            }
        }
    }

    /**
     * Changes the client's main bank account.
     *
     * @param account new main bank account
     */
    public void setMainAccount(Account account)
    {
        if (accounts.contains(account))
        {
            this.mainAccount = account;
        }
        else
        {
            System.out.println("Bank account not owned by user!");
        }
    }

    /**
     * Returns the total balance of all client's bank accounts.
     *
     * @return total client's balance.
     */
    @Override
    public double getBalance()
    {
        double sum = 0;

        for (Account account : this.getAccounts())
        {
            sum += account.getBalance();
        }

        return sum;
    }

    @Override
    public String getNumber()
    {
        return this.getMainAccount().getNumber();
    }

    @Override
    public List<String> getTransactionHistory()
    {
        return this.getMainAccount().getTransactionHistory();
    }

    /**
     * Deposits money to the client's main bank account.
     *
     * @param amount amount to deposit
     */
    @Override
    public void deposit(double amount) throws NullPointerException
    {
        if (amount > 0)
        {
            this.getMainAccount().deposit(amount);
        }
    }

    /**
     * Withdraws money from any of the client's bank accounts.
     *
     * @param amount amount to withdraw
     * @return whether the withdraw operation was successful
     */
    @Override
    public boolean withdraw(double amount)
    {
        if (amount > 0 && this.getBalance() >= amount)
        {
            if (this.getMainAccount().getBalance() >= amount)
            {
                this.getMainAccount().withdraw(amount);
            }
            else
            {
                double amountRemaining = amount;

                for (Account account : this.getAccounts())
                {
                    double balance = account.getBalance();

                    if (amountRemaining >= balance)
                    {
                        account.withdraw(balance);
                        amountRemaining -= balance;
                    }
                    else
                    {
                        account.withdraw(amountRemaining);
                        return true;
                    }
                }
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Withdraws money, even if the balance of all of
     * the client's bank accounts is insufficient.
     *
     * @param amount amount to forcefully withdraw
     */
    public void forceWithdraw(double amount)
    {
        if (amount > 0)
        {
            double balance = this.getBalance();
            double amountRemaining = amount;

            if (amountRemaining > balance)
            {
                this.withdraw(balance);
                amountRemaining -= balance;
                this.getMainAccount().forceWithdraw(amountRemaining);
            }
            else
            {
                this.withdraw(amountRemaining);
            }
        }
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
        return this.getMainAccount().sendMoney(balance, amount);
    }
}
