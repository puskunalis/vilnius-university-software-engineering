package lt.puskunalis;

import java.util.List;

/**
 * Represents a balance with deposit and withdraw operations.
 */
public interface Balance
{
    /**
     * Returns the current balance.
     *
     * @return balance
     */
    double getBalance();

    /**
     * Returns the balance's identification number.
     *
     * @return balance's identification number
     */
    String getNumber();

    /**
     * Returns the transaction history.
     *
     * @return transaction history
     */
    List<String> getTransactionHistory();

    /**
     * Deposits money.
     *
     * @param amount amount to deposit
     */
    void deposit(double amount);

    /**
     * Withdraws money if the balance is sufficient.
     *
     * @param amount amount to withdraw
     * @return was withdraw operation successful
     */
    boolean withdraw(double amount);

    /**
     * Withdraws money, even if the balance is insufficient.
     *
     * @param amount amount to forcefully withdraw
     */
    void forceWithdraw(double amount);

    /**
     * Sends money to another balance.
     *
     * @param balance balance to send money to
     * @param amount amount to send
     * @return was transfer operation successful
     */
    boolean sendMoney(Balance balance, double amount);
}
