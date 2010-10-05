file = [pSB1A3.xml]

MoDeL
{
	part
	{
		biobrick id = [pSB1A3], name = [pSB1A3]
		{
			interface
			{
				url:[http://partsregistry.org/cgi/xml/part.cgi?part=pSB1A3];
				shortDesc:[High copy BioBrick assembly plasmid];
			}
			listOfConditionalParameters
			{
				conditionalParameter id = [copyNumber], name = [copy number of plasmid], commonValue = [], units = [per_second]
				{
					parameterValue:[200] compartment = [E_coli];
				}
			}
			listOfReferencedSpecies
			{
				referencedSpecies:[tm_pSB1A3] partType = [ForwardDNA];
			}
		}
	}
}


