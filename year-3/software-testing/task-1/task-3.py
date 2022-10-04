import time
import unittest

from selenium import webdriver
from selenium.common.exceptions import ElementNotVisibleException, ElementNotSelectableException
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.wait import WebDriverWait

def add_new_record(driver):
    driver.find_element(By.ID, "addNewRecordButton").click()

    driver.find_element(By.ID, "firstName").send_keys("FirstName")
    driver.find_element(By.ID, "lastName").send_keys("LastName")
    driver.find_element(By.ID, "userEmail").send_keys("email@example.com")
    driver.find_element(By.ID, "age").send_keys("30")
    driver.find_element(By.ID, "salary").send_keys("100000")
    driver.find_element(By.ID, "department").send_keys("Test Department")

    driver.find_element(By.ID, "submit").click()

    next_button = driver.find_element(By.XPATH, "//button[text() = 'Next']")
    return not next_button.get_property('disabled')

class DemoQATest(unittest.TestCase):

    def setUp(self):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(60)

    def test_progress_bar(self):
        driver = self.driver

        driver.get("https://demoqa.com/")

        driver.find_element(By.XPATH, "//h5[text() = 'Widgets']").click()

        progress_bar = driver.find_element(By.XPATH, "//span[text() = 'Progress Bar']")
        driver.execute_script("arguments[0].scrollIntoView();", progress_bar)
        progress_bar.click()

        driver.find_element(By.ID, "startStopButton").click()
        
        self.assertIsNotNone(driver.find_element(By.XPATH, "//div[@aria-valuenow = '100']"))

        # Don't click the reset button too quickly as that bugs out the progress bar
        time.sleep(1)

        driver.find_element(By.XPATH, "//*[@id = 'resetButton']").click()

        self.assertIsNotNone(driver.find_element(By.XPATH, "//div[@aria-valuenow = '0']"))

    def test_web_tables(self):
        driver = self.driver

        driver.get("https://demoqa.com/")

        driver.find_element(By.XPATH, "//h5[text() = 'Elements']").click()

        driver.find_element(By.XPATH, "//span[text() = 'Web Tables']").click()

        wait = WebDriverWait(driver, timeout=60, poll_frequency=0, ignored_exceptions=[ElementNotVisibleException, ElementNotSelectableException])
        wait.until(add_new_record)

        next_button = driver.find_element(By.XPATH, "//button[text() = 'Next']")
        driver.execute_script("arguments[0].scrollIntoView();", next_button)
        next_button.click()

        driver.find_element(By.XPATH, "//span[@Title = 'Delete']").click()

        total_pages = driver.find_element(By.XPATH, "//span[@class = '-totalPages']")

        self.assertEqual(str(total_pages.text), "1")

    def tearDown(self):
        self.driver.quit()

if __name__ == "__main__":
    unittest.main()
