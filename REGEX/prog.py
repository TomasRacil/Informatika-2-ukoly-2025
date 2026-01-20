import re

EMAIL_RE = re.compile(r'([^\s<>"\'()]+)@([A-Za-z0-9.-]+\.[A-Za-z]{2,})')

with open("REGEX/final_dump.txt", "r", encoding="utf-8") as f:
    text = f.read()

emails = []

unikat_email = []

unikat_user_8 = []

def denoise(username):
    return re.sub(r'[^A-Za-z]', '', username)

for match in EMAIL_RE.finditer(text):
    user = denoise(match.group(1))
    domain = match.group(2)
    emails.append(f"{user}@{domain}")
    if len(user) == 8:
        unikat_user_8.append(user)

for email in emails:
    if email not in unikat_email:
        unikat_email.append(email)


def modul2_krypto_transakce(data):
   
    hash_pattern = r'0x[0-9a-fA-F]{16,64}'

    lines = data.split('\n')
    last_confirmed_hash = None
    
    for line in lines:
        matches = re.findall(hash_pattern, line)
        if matches:
            if re.search(r'\b(confirmed|success|approved|verified)\b', line, re.IGNORECASE):
                last_confirmed_hash = matches[-1]
    
    if last_confirmed_hash:
        digits_sum = sum(int(c) for c in last_confirmed_hash if c.isdigit())
        print(f"MODUL 2: Poslední potvrzený hash: {last_confirmed_hash}")
        print(f"MODUL 2: Součet číslic: {digits_sum}")
        return digits_sum
    
    
    

print(modul2_krypto_transakce("REGEX/final_dump.txt"))


def modul4_mac_adresy(data):
    mac_pattern = r'\b([0-9A-Fa-f]{2})[:-]([0-9A-Fa-f]{2})[:-]([0-9A-Fa-f]{2})[:-]([0-9A-Fa-f]{2})[:-]([0-9A-Fa-f]{2})[:-]([0-9A-Fa-f]{2})\b'
    
    last_valid_mac = None
    
    for match in re.finditer(mac_pattern, data):
        first_byte = match.group(1).upper()
        if first_byte != 'FF':
            last_valid_mac = match.groups()
    
    if last_valid_mac:
        third_byte = last_valid_mac[2].upper()
        mac_str = ':'.join(last_valid_mac)
        print(f"MODUL 4: Poslední platná MAC: {mac_str}")
        print(f"MODUL 4: Třetí byte: {third_byte}")
        return third_byte
    
    print("MODUL 4: Nebyla nalezena žádná platná MAC adresa")
    return "00"

print(modul4_mac_adresy("REGEX/final_dump.txt"))
