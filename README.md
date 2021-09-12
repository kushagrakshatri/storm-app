# Storm-App
A storm event application that manages storm event data and uses it to answer queries meeting given selection criteria.

## Getting Started
### Requirements
- [gcc](https://gcc.gnu.org/install/)

- Storm event and Fatalities data csv files ranging between the years 1950-2019

### Installation

```
cd ./storm-app
Makefile
```


# Usage
## For loading the storm and fatalities data

The syntax is:-


```
storm n YYYY...YYYY  ('n' is the number of years) (YYYY denote the years between 1950-2019, each having space between them)

```

### Example

```
storm 2 1954 1956
```

## For processing the user queries

The syntax is:-

```
q (the number of user queries)
'q' queries (one per line)

```

### Example

```
2
select max 1950 damage_crops insertion
select 3 all fatality merge
```



