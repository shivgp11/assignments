-- run BEFORE projectInsert.sql

drop trigger if exists ensure_data_consistency;
delimiter // 
CREATE TRIGGER ensure_data_consistency BEFORE INSERT ON users
FOR EACH ROW
BEGIN
    if NEW.state = 'Alabama' THEN
		SET NEW.state = 'AL'; 
        END IF;
	if NEW.state = 'Alaska' THEN
		SET NEW.state = 'AK';
        END IF;
	if NEW.state = 'Arizona' THEN
		SET NEW.state = 'AZ';
        END IF;
	if NEW.state = 'Arkansas' THEN
		SET NEW.state = 'AR';
        END IF;
	if NEW.state = 'California' THEN
		SET NEW.state = 'CA';
        END IF;
	if NEW.state = 'Colorado' THEN
		SET NEW.state = 'CO';
        END IF;
	if NEW.state = 'Connecticut' THEN
		SET NEW.state = 'CT';
        END IF;
	if NEW.state = 'Delaware' THEN
		SET NEW.state = 'DE';
        END IF;
	if NEW.state = 'Florida' THEN
		SET NEW.state = 'FL';
        END IF;
	if NEW.state = 'Georgia' THEN
		SET NEW.state = 'GA';
        END IF;
	if NEW.state = 'Hawaii' THEN
		SET NEW.state = 'HI';
        END IF;
	if NEW.state = 'Idaho' THEN
		SET NEW.state = 'ID';
        END IF;
	if NEW.state = 'Illinois' THEN
		SET NEW.state = 'IL';
        END IF;
	if NEW.state = 'Indiana' THEN
		SET NEW.state = 'IN';
        END IF;
	if NEW.state = 'Iowa' THEN
		SET NEW.state = 'IA';
        END IF;
	if NEW.state = 'Kansas' THEN
		SET NEW.state = 'KS';
        END IF;
	if NEW.state = 'Kentucky' THEN
		SET NEW.state = 'KY';
        END IF;
	if NEW.state = 'Louisiana' THEN
		SET NEW.state = 'LA';
        END IF;
	if NEW.state = 'Maine' THEN
		SET NEW.state = 'ME';
        END IF;
	if NEW.state = 'Maryland' THEN
		SET NEW.state = 'MD';
        END IF;
	if NEW.state = 'Massachusetts' THEN
		SET NEW.state = 'MA';
        END IF;
	if NEW.state = 'Michigan' THEN
		SET NEW.state = 'MI';
        END IF;
	if NEW.state = 'Minnesota' THEN
		SET NEW.state = 'MN';
        END IF;
	if NEW.state = 'Mississippi' THEN
		SET NEW.state = 'MS';
        END IF;
	if NEW.state = 'Missouri' THEN
		SET NEW.state = 'MO';
        END IF;
	if NEW.state = 'Montana' THEN
		SET NEW.state = 'MT';
        END IF;
	if NEW.state = 'Nebraska' THEN
		SET NEW.state = 'NE';
        END IF;
	if NEW.state = 'Nevada' THEN
		SET NEW.state = 'NV';
        END IF;
	if NEW.state = 'New Hampshire' THEN
		SET NEW.state = 'NH';
        END IF;
	if NEW.state = 'New Jersey' THEN
		SET NEW.state = 'NJ';
        END IF;
	if NEW.state = 'New Mexico' THEN
		SET NEW.state = 'NM';
        END IF;
	if NEW.state = 'New York' THEN
		SET NEW.state = 'NY';
        END IF;
	if NEW.state = 'North Carolina' THEN
		SET NEW.state = 'NC';
        END IF;
	if NEW.state = 'North Dakota' THEN
		SET NEW.state = 'ND';
        END IF;
	if NEW.state = 'Ohio' THEN
		SET NEW.state = 'OH';
        END IF;
	if NEW.state = 'Oklahoma' THEN
		SET NEW.state = 'OK';
        END IF;
	if NEW.state = 'Oregon' THEN
		SET NEW.state = 'OR';
        END IF;
	if NEW.state = 'Pennsylvania' THEN
		SET NEW.state = 'PA';
        END IF;
	if NEW.state = 'Rhode Island' THEN
		SET NEW.state = 'RI';
        END IF;
	if NEW.state = 'South Carolina' THEN
		SET NEW.state = 'SA';
        END IF;
	if NEW.state = 'South Dakota' THEN
		SET NEW.state = 'SD';
        END IF;
	if NEW.state = 'Tennessee' THEN
		SET NEW.state = 'TN';
        END IF;
	if NEW.state = 'Texas' THEN
		SET NEW.state = 'TX';
        END IF;
	if NEW.state = 'Utah' THEN
		SET NEW.state = 'UT';
        END IF;
	if NEW.state = 'Vermont' THEN
		SET NEW.state = 'VT';
        END IF;
	if NEW.state = 'Virginia' THEN
		SET NEW.state = 'VA';
        END IF;
	if NEW.state = 'Washington' THEN
		SET NEW.state = 'WA';
        END IF;
	if NEW.state = 'West Virginia' THEN
		SET NEW.state = 'WV';
        END IF;
	if NEW.state = 'Wisconsin' THEN
		SET NEW.state = 'WI';
        END IF;
	if NEW.state = 'Wyoming' THEN
		SET NEW.state = 'WY';
        END IF;
        END;//
        
delimiter ;