file = [TE145.xml]

MoDeL
{
	part
	{
		biobrick id = [TE145], name = [T7TE (BBa_B0012)]
		{
			interface
			{
				url:[http://partsregistry.org/cgi/xml/part.cgi?part=BBa_B0012];
				shortDesc:[TE from coliphageT7]; 
			}
			listOfConditionalParameters
			{
				conditionalParameter id = [forwardTerminatorEfficiency], name = [efficiency as a Terminator when transcripted forward], commonValue = [], units = [per_second]
				{
					parameterValue:[0.309] compartment = [E_coli];
				}
			}
			listOfReferencedSpecies
			{
			}
		}
	}
}
