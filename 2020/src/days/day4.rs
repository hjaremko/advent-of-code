use crate::utils::Day;
use aoc_fetch::AocInput;
use std::collections::HashMap;
// use log::debug;

pub struct Day4 {
    passes: Vec<Passport>,
}

impl Day4 {
    fn parse_passports(input: AocInput) -> Vec<Passport> {
        input
            .split_by::<String>("\n\n")
            .iter()
            .map(|raw| Passport::make(raw))
            .collect()
    }
}

impl Day for Day4 {
    fn new(input: AocInput) -> Self {
        Day4 {
            passes: Day4::parse_passports(input),
        }
    }

    fn get_first_solution(&self) -> String {
        self.passes
            .iter()
            .filter(|p| p.has_all_fields() || p.has_all_but_cid())
            .count()
            .to_string()
    }

    fn get_second_solution(&self) -> String {
        self.passes
            .iter()
            .filter(|p| p.validate())
            .count()
            .to_string()
    }
}

#[derive(Debug)]
struct Passport {
    fields: HashMap<String, String>,
}

impl Passport {
    fn make(raw: &String) -> Self {
        let mut p = HashMap::new();

        raw.split_whitespace().for_each(|kv| {
            let kv = kv.split(':').collect::<Vec<&str>>();
            p.insert(kv[0].to_string(), kv[1].to_string());
        });

        Passport { fields: p }
    }

    fn val_year(&self, key: &str, low: i32, high: i32) -> bool {
        let iyr: i32 = self.fields.get(key).unwrap().parse().ok().unwrap();
        low <= iyr && iyr <= high
    }

    fn has_all_fields(&self) -> bool {
        self.fields.len() == 8
    }

    fn has_all_but_cid(&self) -> bool {
        self.fields.len() == 7 && !self.fields.contains_key("cid")
    }

    fn validate_hgt(&self) -> bool {
        let validate = |hgt: &String, unit: &str, low: i32, high: i32| {
            let h = hgt.replace(unit, "");
            let v: i32 = h.parse().ok().unwrap();

            low <= v && v <= high
        };

        let hgt = self.fields.get("hgt").unwrap();

        if hgt.contains("cm") {
            validate(hgt, "cm", 150, 193)
        } else {
            validate(hgt, "in", 59, 76)
        }
    }

    fn validate_hcl(&self) -> bool {
        let hcl = self.fields.get("hcl").unwrap();

        hcl.chars().nth(0).unwrap() == '#'
            && hcl.len() == 7
            && hcl
                .chars()
                .skip(1)
                .all(|c| c.is_ascii_digit() || c >= 'a' && c <= 'f')
    }

    fn validate_ecl(&self) -> bool {
        let cols = vec!["amb", "blu", "brn", "gry", "grn", "hzl", "oth"];
        cols.contains(&&**self.fields.get("ecl").unwrap())
    }

    fn validate_pid(&self) -> bool {
        let pid = self.fields.get("pid").unwrap();
        pid.len() == 9 && pid.chars().all(|c| c.is_ascii_digit())
    }

    fn validate(&self) -> bool {
        if !self.has_all_fields() && !self.has_all_but_cid() {
            return false;
        }

        let byrv = self.val_year("byr", 1920, 2002);
        let iyrv = self.val_year("iyr", 2010, 2020);
        let eyrv = self.val_year("eyr", 2020, 2030);
        let hgbv = self.validate_hgt();
        let hclv = self.validate_hcl();
        let eclv = self.validate_ecl();
        let pidv = self.validate_pid();

        byrv && iyrv && eyrv && pidv && eclv && hgbv && hclv
    }
}
