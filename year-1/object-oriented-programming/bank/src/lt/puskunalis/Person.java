package lt.puskunalis;

import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.Setter;

/**
 * Represents a person.
 */
@EqualsAndHashCode
@Getter
public class Person
{
    @Setter
    private String name;

    private final int birthYear;

    @Setter
    private String address;

    public Person(String name, int birthYear, String address)
    {
        this.name = name;
        this.birthYear = birthYear;
        this.address = address;
    }
}
